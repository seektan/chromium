// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_JS_SYNC_MANAGER_OBSERVER_H_
#define SYNC_INTERNAL_API_JS_SYNC_MANAGER_OBSERVER_H_
#pragma once

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "sync/internal_api/sync_manager.h"
#include "sync/protocol/sync_protocol_error.h"
#include "sync/util/weak_handle.h"

namespace tracked_objects {
class Location;
}  // namespace tracked_objects

namespace browser_sync {

class JsEventDetails;
class JsEventHandler;

// Routes SyncManager events to a JsEventHandler.
class JsSyncManagerObserver : public sync_api::SyncManager::Observer {
 public:
  JsSyncManagerObserver();
  virtual ~JsSyncManagerObserver();

  void SetJsEventHandler(const WeakHandle<JsEventHandler>& event_handler);

  // sync_api::SyncManager::Observer implementation.
  virtual void OnSyncCycleCompleted(
      const sessions::SyncSessionSnapshot& snapshot) OVERRIDE;
  virtual void OnConnectionStatusChange(
      sync_api::ConnectionStatus status) OVERRIDE;
  virtual void OnUpdatedToken(const std::string& token) OVERRIDE;
  virtual void OnPassphraseRequired(
      sync_api::PassphraseRequiredReason reason,
      const sync_pb::EncryptedData& pending_keys) OVERRIDE;
  virtual void OnPassphraseAccepted() OVERRIDE;
  virtual void OnBootstrapTokenUpdated(
      const std::string& bootstrap_token) OVERRIDE;
  virtual void OnEncryptedTypesChanged(
      syncable::ModelTypeSet encrypted_types,
      bool encrypt_everything) OVERRIDE;
  virtual void OnEncryptionComplete() OVERRIDE;
  virtual void OnInitializationComplete(
      const WeakHandle<JsBackend>& js_backend, bool success) OVERRIDE;
  virtual void OnStopSyncingPermanently() OVERRIDE;
  virtual void OnClearServerDataSucceeded() OVERRIDE;
  virtual void OnClearServerDataFailed() OVERRIDE;
  virtual void OnActionableError(
      const browser_sync::SyncProtocolError& sync_protocol_error) OVERRIDE;

 private:
  void HandleJsEvent(const tracked_objects::Location& from_here,
                    const std::string& name, const JsEventDetails& details);

  WeakHandle<JsEventHandler> event_handler_;

  DISALLOW_COPY_AND_ASSIGN(JsSyncManagerObserver);
};

}  // namespace browser_sync

#endif  // SYNC_INTERNAL_API_JS_SYNC_MANAGER_OBSERVER_H_
