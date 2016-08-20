#include "CItem.h"
#include "CItemGeneral.h"

int CItem::g_nMaxIID;
std::mutex CItem::g_mxMaxIID;

CItem::CItem(ITEMINFO_DESC& desc)
{
	m_desc = desc;
}

CItem::~CItem()
{
	while (m_Access.IsBusy()) {
		printf("CItem::~CItem: Item is in use, can't delete! Retrying in 10ms...\n");
		usleep(10000);
	}
}

int CItem::NewIID()
{
	g_mxMaxIID.lock();
	g_nMaxIID++;
	g_mxMaxIID.unlock();

	return g_nMaxIID;
}

CItem* CItem::CreateItem(ITEMINFO_DESC& desc)
{
	CItemInfo* pMacro = (CItemInfo*) CMacroDB::FindMacro(CMacro::MT_ITEM, desc.wIndex);
	if (!pMacro) {
		printf(KRED "Wrong item index: %d\n" KNRM, desc.wIndex);
		return NULL;
	}

	CItem *pItem=NULL;

	switch (pMacro->m_byClass)
	{
		case IC_GENERAL:
			pItem = new CItemGeneral(desc);
			break;
		default:
			printf(KRED "Unknown item class (%d). Creating ItemGeneral then.\n" KNRM, pMacro->m_byClass);
			pItem = new CItemGeneral(desc);
			break;
	}

	if (pItem)
		pItem->m_pMacro = pMacro;

	return pItem;
}